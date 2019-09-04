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
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_scomp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zip_comp_deflate ; 
 int /*<<< orphan*/  zip_comp_lzs ; 
 int /*<<< orphan*/  zip_scomp_deflate ; 
 int /*<<< orphan*/  zip_scomp_lzs ; 

__attribute__((used)) static void zip_unregister_compression_device(void)
{
	crypto_unregister_alg(&zip_comp_deflate);
	crypto_unregister_alg(&zip_comp_lzs);
	crypto_unregister_scomp(&zip_scomp_deflate);
	crypto_unregister_scomp(&zip_scomp_lzs);
}