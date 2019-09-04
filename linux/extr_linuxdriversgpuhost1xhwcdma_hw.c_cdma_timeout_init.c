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
struct TYPE_2__ {int initialized; int /*<<< orphan*/  wq; } ;
struct host1x_cdma {TYPE_1__ timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdma_timeout_handler ; 

__attribute__((used)) static int cdma_timeout_init(struct host1x_cdma *cdma, unsigned int syncpt)
{
	INIT_DELAYED_WORK(&cdma->timeout.wq, cdma_timeout_handler);
	cdma->timeout.initialized = true;

	return 0;
}