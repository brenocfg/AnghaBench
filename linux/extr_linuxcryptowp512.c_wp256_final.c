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
struct shash_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WP256_DIGEST_SIZE ; 
 int /*<<< orphan*/  WP512_DIGEST_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memzero_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wp512_final (struct shash_desc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wp256_final(struct shash_desc *desc, u8 *out)
{
	u8 D[64];

	wp512_final(desc, D);
	memcpy(out, D, WP256_DIGEST_SIZE);
	memzero_explicit(D, WP512_DIGEST_SIZE);

	return 0;
}