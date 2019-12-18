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
struct mei_msg_hdr {int /*<<< orphan*/  length; } ;
struct mei_device {int dummy; } ;

/* Variables and functions */
 int mei_write_message (struct mei_device*,struct mei_msg_hdr*,int,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int mei_hbm_write_message(struct mei_device *dev,
					struct mei_msg_hdr *hdr,
					const void *data)
{
	return mei_write_message(dev, hdr, sizeof(*hdr), data, hdr->length);
}