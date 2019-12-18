#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct user_key_payload {int /*<<< orphan*/  data; int /*<<< orphan*/  datalen; } ;
struct key {int /*<<< orphan*/  sem; } ;
struct dm_verity_sig_opts {int /*<<< orphan*/  sig_size; int /*<<< orphan*/  sig; } ;

/* Variables and functions */
 int EKEYREVOKED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  key_type_user ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct key* request_key (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 struct user_key_payload* user_key_payload_locked (struct key*) ; 

__attribute__((used)) static int verity_verify_get_sig_from_key(const char *key_desc,
					struct dm_verity_sig_opts *sig_opts)
{
	struct key *key;
	const struct user_key_payload *ukp;
	int ret = 0;

	key = request_key(&key_type_user,
			key_desc, NULL);
	if (IS_ERR(key))
		return PTR_ERR(key);

	down_read(&key->sem);

	ukp = user_key_payload_locked(key);
	if (!ukp) {
		ret = -EKEYREVOKED;
		goto end;
	}

	sig_opts->sig = kmalloc(ukp->datalen, GFP_KERNEL);
	if (!sig_opts->sig) {
		ret = -ENOMEM;
		goto end;
	}
	sig_opts->sig_size = ukp->datalen;

	memcpy(sig_opts->sig, ukp->data, sig_opts->sig_size);

end:
	up_read(&key->sem);
	key_put(key);

	return ret;
}