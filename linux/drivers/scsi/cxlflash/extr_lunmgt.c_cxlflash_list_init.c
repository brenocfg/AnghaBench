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
struct TYPE_2__ {int /*<<< orphan*/ * err_page; int /*<<< orphan*/  mutex; int /*<<< orphan*/  gluns; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_1__ global ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void cxlflash_list_init(void)
{
	INIT_LIST_HEAD(&global.gluns);
	mutex_init(&global.mutex);
	global.err_page = NULL;
}