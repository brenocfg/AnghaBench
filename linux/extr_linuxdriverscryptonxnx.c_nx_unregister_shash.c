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
typedef  int /*<<< orphan*/  u32 ;
struct shash_alg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_unregister_shash (struct shash_alg*) ; 
 scalar_t__ nx_check_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nx_check_props (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nx_unregister_shash(struct shash_alg *alg, u32 fc, u32 mode,
				int slot)
{
	if (slot >= 0 ? nx_check_prop(NULL, fc, mode, slot) :
			nx_check_props(NULL, fc, mode))
		crypto_unregister_shash(alg);
}