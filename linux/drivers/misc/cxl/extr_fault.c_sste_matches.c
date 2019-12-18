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
struct cxl_sste {scalar_t__ vsid_data; scalar_t__ esid_data; } ;
struct copro_slb {int /*<<< orphan*/  esid; int /*<<< orphan*/  vsid; } ;

/* Variables and functions */
 scalar_t__ cpu_to_be64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool sste_matches(struct cxl_sste *sste, struct copro_slb *slb)
{
	return ((sste->vsid_data == cpu_to_be64(slb->vsid)) &&
		(sste->esid_data == cpu_to_be64(slb->esid)));
}