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
typedef  int u32 ;
struct ocrdma_dev {int dummy; } ;

/* Variables and functions */
#define  BE_DEV_SHUTDOWN 128 
 int /*<<< orphan*/  ocrdma_shutdown (struct ocrdma_dev*) ; 

__attribute__((used)) static void ocrdma_event_handler(struct ocrdma_dev *dev, u32 event)
{
	switch (event) {
	case BE_DEV_SHUTDOWN:
		ocrdma_shutdown(dev);
		break;
	default:
		break;
	}
}