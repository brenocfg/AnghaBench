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
struct cyttsp4 {int /*<<< orphan*/  xfer_buf; int /*<<< orphan*/  dev; TYPE_1__* bus_ops; } ;
struct TYPE_2__ {int (* write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void const*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void const*) ; 

__attribute__((used)) static inline int cyttsp4_adap_write(struct cyttsp4 *ts, u16 addr, int size,
		const void *buf)
{
	return ts->bus_ops->write(ts->dev, ts->xfer_buf, addr, size, buf);
}