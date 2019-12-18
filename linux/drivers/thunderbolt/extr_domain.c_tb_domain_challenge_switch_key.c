#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct tb_switch {int /*<<< orphan*/  key; int /*<<< orphan*/  authorized; TYPE_1__ dev; } ;
struct tb {TYPE_2__* cm_ops; } ;
struct shash_desc {struct crypto_shash* tfm; } ;
struct crypto_shash {int dummy; } ;
typedef  int /*<<< orphan*/  hmac ;
typedef  int /*<<< orphan*/  challenge ;
struct TYPE_4__ {int (* approve_switch ) (struct tb*,struct tb_switch*) ;int (* challenge_switch_key ) (struct tb*,struct tb_switch*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EKEYREJECTED ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 int PTR_ERR (struct crypto_shash*) ; 
 int TB_SWITCH_KEY_SIZE ; 
 struct crypto_shash* crypto_alloc_shash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (struct crypto_shash*) ; 
 scalar_t__ crypto_shash_descsize (struct crypto_shash*) ; 
 int crypto_shash_digest (struct shash_desc*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int crypto_shash_setkey (struct crypto_shash*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct shash_desc*) ; 
 struct shash_desc* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct tb*,struct tb_switch*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub2 (struct tb*,struct tb_switch*) ; 
 struct tb_switch* tb_to_switch (int /*<<< orphan*/ ) ; 

int tb_domain_challenge_switch_key(struct tb *tb, struct tb_switch *sw)
{
	u8 challenge[TB_SWITCH_KEY_SIZE];
	u8 response[TB_SWITCH_KEY_SIZE];
	u8 hmac[TB_SWITCH_KEY_SIZE];
	struct tb_switch *parent_sw;
	struct crypto_shash *tfm;
	struct shash_desc *shash;
	int ret;

	if (!tb->cm_ops->approve_switch || !tb->cm_ops->challenge_switch_key)
		return -EPERM;

	/* The parent switch must be authorized before this one */
	parent_sw = tb_to_switch(sw->dev.parent);
	if (!parent_sw || !parent_sw->authorized)
		return -EINVAL;

	get_random_bytes(challenge, sizeof(challenge));
	ret = tb->cm_ops->challenge_switch_key(tb, sw, challenge, response);
	if (ret)
		return ret;

	tfm = crypto_alloc_shash("hmac(sha256)", 0, 0);
	if (IS_ERR(tfm))
		return PTR_ERR(tfm);

	ret = crypto_shash_setkey(tfm, sw->key, TB_SWITCH_KEY_SIZE);
	if (ret)
		goto err_free_tfm;

	shash = kzalloc(sizeof(*shash) + crypto_shash_descsize(tfm),
			GFP_KERNEL);
	if (!shash) {
		ret = -ENOMEM;
		goto err_free_tfm;
	}

	shash->tfm = tfm;

	memset(hmac, 0, sizeof(hmac));
	ret = crypto_shash_digest(shash, challenge, sizeof(hmac), hmac);
	if (ret)
		goto err_free_shash;

	/* The returned HMAC must match the one we calculated */
	if (memcmp(response, hmac, sizeof(hmac))) {
		ret = -EKEYREJECTED;
		goto err_free_shash;
	}

	crypto_free_shash(tfm);
	kfree(shash);

	return tb->cm_ops->approve_switch(tb, sw);

err_free_shash:
	kfree(shash);
err_free_tfm:
	crypto_free_shash(tfm);

	return ret;
}