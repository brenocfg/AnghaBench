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
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOENT ; 
 int __be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * of_get_address (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int anybus_of_get_host_idx(struct device_node *np)
{
	const __be32 *host_idx;

	host_idx = of_get_address(np, 0, NULL, NULL);
	if (!host_idx)
		return -ENOENT;
	return __be32_to_cpu(*host_idx);
}