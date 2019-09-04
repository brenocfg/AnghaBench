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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X86_FEATURE_SSSE3 ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int crypto_register_shashes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sha256_ssse3_algs ; 

__attribute__((used)) static int register_sha256_ssse3(void)
{
	if (boot_cpu_has(X86_FEATURE_SSSE3))
		return crypto_register_shashes(sha256_ssse3_algs,
				ARRAY_SIZE(sha256_ssse3_algs));
	return 0;
}