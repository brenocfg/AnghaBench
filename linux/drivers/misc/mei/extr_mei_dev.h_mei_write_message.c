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
struct mei_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* write ) (struct mei_device*,void const*,size_t,void const*,size_t) ;} ;

/* Variables and functions */
 int stub1 (struct mei_device*,void const*,size_t,void const*,size_t) ; 

__attribute__((used)) static inline int mei_write_message(struct mei_device *dev,
				    const void *hdr, size_t hdr_len,
				    const void *data, size_t data_len)
{
	return dev->ops->write(dev, hdr, hdr_len, data, data_len);
}