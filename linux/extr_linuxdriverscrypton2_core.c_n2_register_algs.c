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

/* Variables and functions */
 int NUM_CIPHER_TMPLS ; 
 int NUM_HASH_TMPLS ; 
 int __n2_register_one_ahash (int /*<<< orphan*/ *) ; 
 int __n2_register_one_cipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __n2_unregister_algs () ; 
 int /*<<< orphan*/  algs_registered ; 
 int /*<<< orphan*/ * cipher_tmpls ; 
 int /*<<< orphan*/ * hash_tmpls ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_lock ; 

__attribute__((used)) static int n2_register_algs(void)
{
	int i, err = 0;

	mutex_lock(&spu_lock);
	if (algs_registered++)
		goto out;

	for (i = 0; i < NUM_HASH_TMPLS; i++) {
		err = __n2_register_one_ahash(&hash_tmpls[i]);
		if (err) {
			__n2_unregister_algs();
			goto out;
		}
	}
	for (i = 0; i < NUM_CIPHER_TMPLS; i++) {
		err = __n2_register_one_cipher(&cipher_tmpls[i]);
		if (err) {
			__n2_unregister_algs();
			goto out;
		}
	}

out:
	mutex_unlock(&spu_lock);
	return err;
}