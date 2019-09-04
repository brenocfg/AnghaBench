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
struct request_queue {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  BLK_ZONED_HA 129 
#define  BLK_ZONED_HM 128 
 int blk_queue_zoned_model (struct request_queue*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t queue_zoned_show(struct request_queue *q, char *page)
{
	switch (blk_queue_zoned_model(q)) {
	case BLK_ZONED_HA:
		return sprintf(page, "host-aware\n");
	case BLK_ZONED_HM:
		return sprintf(page, "host-managed\n");
	default:
		return sprintf(page, "none\n");
	}
}