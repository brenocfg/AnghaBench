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
struct push_buffer {int dummy; } ;
struct host1x {TYPE_1__* cdma_pb_op; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init ) (struct push_buffer*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct push_buffer*) ; 

__attribute__((used)) static inline void host1x_hw_pushbuffer_init(struct host1x *host,
					     struct push_buffer *pb)
{
	host->cdma_pb_op->init(pb);
}