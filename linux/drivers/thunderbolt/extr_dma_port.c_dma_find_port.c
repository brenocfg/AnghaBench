#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tb_switch {TYPE_1__* tb; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  DMA_PORT_TIMEOUT ; 
 int ENODEV ; 
 int TB_TYPE_NHI ; 
 int dma_port_read (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int const,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_route (struct tb_switch*) ; 

__attribute__((used)) static int dma_find_port(struct tb_switch *sw)
{
	static const int ports[] = { 3, 5, 7 };
	int i;

	/*
	 * The DMA (NHI) port is either 3, 5 or 7 depending on the
	 * controller. Try all of them.
	 */
	for (i = 0; i < ARRAY_SIZE(ports); i++) {
		u32 type;
		int ret;

		ret = dma_port_read(sw->tb->ctl, &type, tb_route(sw), ports[i],
				    2, 1, DMA_PORT_TIMEOUT);
		if (!ret && (type & 0xffffff) == TB_TYPE_NHI)
			return ports[i];
	}

	return -ENODEV;
}