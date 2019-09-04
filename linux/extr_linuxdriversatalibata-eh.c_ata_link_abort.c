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
struct ata_link {int /*<<< orphan*/  ap; } ;

/* Variables and functions */
 int ata_do_link_abort (int /*<<< orphan*/ ,struct ata_link*) ; 

int ata_link_abort(struct ata_link *link)
{
	return ata_do_link_abort(link->ap, link);
}