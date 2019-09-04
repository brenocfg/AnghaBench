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
 int ata_sff_softreset (struct ata_link*,unsigned int*,unsigned long) ; 
 int /*<<< orphan*/  pdc_reset_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pdc_softreset(struct ata_link *link, unsigned int *class,
			 unsigned long deadline)
{
	pdc_reset_port(link->ap);
	return ata_sff_softreset(link, class, deadline);
}