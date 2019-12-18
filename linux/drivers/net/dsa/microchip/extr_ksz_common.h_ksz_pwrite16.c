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
typedef  int /*<<< orphan*/  u16 ;
struct ksz_device {TYPE_1__* dev_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_port_addr ) (int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ksz_write16 (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int) ; 

__attribute__((used)) static inline void ksz_pwrite16(struct ksz_device *dev, int port, int offset,
				u16 data)
{
	ksz_write16(dev, dev->dev_ops->get_port_addr(port, offset), data);
}