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
typedef  scalar_t__ u16 ;
struct mii_bus {scalar_t__ (* write ) (struct mii_bus*,int,int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ qca8k_current_page ; 
 scalar_t__ stub1 (struct mii_bus*,int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
qca8k_set_page(struct mii_bus *bus, u16 page)
{
	if (page == qca8k_current_page)
		return;

	if (bus->write(bus, 0x18, 0, page) < 0)
		dev_err_ratelimited(&bus->dev,
				    "failed to set qca8k page\n");
	qca8k_current_page = page;
}