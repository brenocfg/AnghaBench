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
 int /*<<< orphan*/  __of_get_dma_parent ; 
 int /*<<< orphan*/  __of_translate_address (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char*,struct device_node**) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

u64 of_translate_dma_address(struct device_node *dev, const __be32 *in_addr)
{
	struct device_node *host;
	u64 ret;

	ret = __of_translate_address(dev, __of_get_dma_parent,
				     in_addr, "dma-ranges", &host);

	if (host) {
		of_node_put(host);
		return OF_BAD_ADDR;
	}

	return ret;
}