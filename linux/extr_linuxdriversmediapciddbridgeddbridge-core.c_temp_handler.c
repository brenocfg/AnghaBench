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
struct ddb_link {int /*<<< orphan*/  temp_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tempmon_setfan (struct ddb_link*) ; 

__attribute__((used)) static void temp_handler(void *data)
{
	struct ddb_link *link = (struct ddb_link *)data;

	spin_lock(&link->temp_lock);
	tempmon_setfan(link);
	spin_unlock(&link->temp_lock);
}