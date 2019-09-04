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
struct ide_host {int dummy; } ;
struct expansion_card {int dummy; } ;

/* Variables and functions */
 struct ide_host* ecard_get_drvdata (struct expansion_card*) ; 
 int /*<<< orphan*/  ecard_release_resources (struct expansion_card*) ; 
 int /*<<< orphan*/  ecard_set_drvdata (struct expansion_card*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ide_host_remove (struct ide_host*) ; 

__attribute__((used)) static void rapide_remove(struct expansion_card *ec)
{
	struct ide_host *host = ecard_get_drvdata(ec);

	ecard_set_drvdata(ec, NULL);

	ide_host_remove(host);

	ecard_release_resources(ec);
}