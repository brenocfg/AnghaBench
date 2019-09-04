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
typedef  int u32 ;
struct test_mb_aead_data {int /*<<< orphan*/  wait; int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int ENCRYPT ; 
 int crypto_aead_decrypt (int /*<<< orphan*/ ) ; 
 int crypto_aead_encrypt (int /*<<< orphan*/ ) ; 
 int crypto_wait_req (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 

__attribute__((used)) static int do_mult_aead_op(struct test_mb_aead_data *data, int enc,
				u32 num_mb, int *rc)
{
	int i, err = 0;

	/* Fire up a bunch of concurrent requests */
	for (i = 0; i < num_mb; i++) {
		if (enc == ENCRYPT)
			rc[i] = crypto_aead_encrypt(data[i].req);
		else
			rc[i] = crypto_aead_decrypt(data[i].req);
	}

	/* Wait for all requests to finish */
	for (i = 0; i < num_mb; i++) {
		rc[i] = crypto_wait_req(rc[i], &data[i].wait);

		if (rc[i]) {
			pr_info("concurrent request %d error %d\n", i, rc[i]);
			err = rc[i];
		}
	}

	return err;
}