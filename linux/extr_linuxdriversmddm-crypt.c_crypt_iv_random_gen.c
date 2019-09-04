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
typedef  int /*<<< orphan*/  u8 ;
struct dm_crypt_request {int dummy; } ;
struct crypt_config {int /*<<< orphan*/  iv_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypt_iv_random_gen(struct crypt_config *cc, u8 *iv,
				struct dm_crypt_request *dmreq)
{
	/* Used only for writes, there must be an additional space to store IV */
	get_random_bytes(iv, cc->iv_size);
	return 0;
}