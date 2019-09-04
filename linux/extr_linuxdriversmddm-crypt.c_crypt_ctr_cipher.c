#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct dm_target {char* error; struct crypt_config* private; } ;
struct crypt_config {int key_size; int /*<<< orphan*/  key; scalar_t__ key_string; TYPE_1__* iv_gen_ops; int /*<<< orphan*/  cipher_string; } ;
struct TYPE_2__ {int (* ctr ) (struct crypt_config*,struct dm_target*,char*) ;int (* init ) (struct crypt_config*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int crypt_ctr_cipher_new (struct dm_target*,char*,char*,char**,char**) ; 
 int crypt_ctr_cipher_old (struct dm_target*,char*,char*,char**,char**) ; 
 int crypt_ctr_ivmode (struct dm_target*,char*) ; 
 int crypt_set_key (struct crypt_config*,char*) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strstarts (char*,char*) ; 
 int stub1 (struct crypt_config*,struct dm_target*,char*) ; 
 int stub2 (struct crypt_config*) ; 

__attribute__((used)) static int crypt_ctr_cipher(struct dm_target *ti, char *cipher_in, char *key)
{
	struct crypt_config *cc = ti->private;
	char *ivmode = NULL, *ivopts = NULL;
	int ret;

	cc->cipher_string = kstrdup(cipher_in, GFP_KERNEL);
	if (!cc->cipher_string) {
		ti->error = "Cannot allocate cipher strings";
		return -ENOMEM;
	}

	if (strstarts(cipher_in, "capi:"))
		ret = crypt_ctr_cipher_new(ti, cipher_in, key, &ivmode, &ivopts);
	else
		ret = crypt_ctr_cipher_old(ti, cipher_in, key, &ivmode, &ivopts);
	if (ret)
		return ret;

	/* Initialize IV */
	ret = crypt_ctr_ivmode(ti, ivmode);
	if (ret < 0)
		return ret;

	/* Initialize and set key */
	ret = crypt_set_key(cc, key);
	if (ret < 0) {
		ti->error = "Error decoding and setting key";
		return ret;
	}

	/* Allocate IV */
	if (cc->iv_gen_ops && cc->iv_gen_ops->ctr) {
		ret = cc->iv_gen_ops->ctr(cc, ti, ivopts);
		if (ret < 0) {
			ti->error = "Error creating IV";
			return ret;
		}
	}

	/* Initialize IV (set keys for ESSIV etc) */
	if (cc->iv_gen_ops && cc->iv_gen_ops->init) {
		ret = cc->iv_gen_ops->init(cc);
		if (ret < 0) {
			ti->error = "Error initialising IV";
			return ret;
		}
	}

	/* wipe the kernel key payload copy */
	if (cc->key_string)
		memset(cc->key, 0, cc->key_size * sizeof(u8));

	return ret;
}