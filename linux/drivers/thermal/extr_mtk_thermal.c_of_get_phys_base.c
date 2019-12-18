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
typedef  int /*<<< orphan*/  u64 ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  OF_BAD_ADDR ; 
 int /*<<< orphan*/ * of_get_address (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_translate_address (struct device_node*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static u64 of_get_phys_base(struct device_node *np)
{
	u64 size64;
	const __be32 *regaddr_p;

	regaddr_p = of_get_address(np, 0, &size64, NULL);
	if (!regaddr_p)
		return OF_BAD_ADDR;

	return of_translate_address(np, regaddr_p);
}