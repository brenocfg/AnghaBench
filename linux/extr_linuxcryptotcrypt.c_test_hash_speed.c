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
struct hash_speed {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 void test_ahash_speed_common (char const*,unsigned int,struct hash_speed*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_hash_speed(const char *algo, unsigned int secs,
			    struct hash_speed *speed)
{
	return test_ahash_speed_common(algo, secs, speed, CRYPTO_ALG_ASYNC);
}