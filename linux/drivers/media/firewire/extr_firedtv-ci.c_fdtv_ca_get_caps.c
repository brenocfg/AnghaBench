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
struct ca_caps {int slot_num; int descr_num; int /*<<< orphan*/  descr_type; int /*<<< orphan*/  slot_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA_CI ; 
 int /*<<< orphan*/  CA_ECD ; 

__attribute__((used)) static int fdtv_ca_get_caps(void *arg)
{
	struct ca_caps *cap = arg;

	cap->slot_num = 1;
	cap->slot_type = CA_CI;
	cap->descr_num = 1;
	cap->descr_type = CA_ECD;
	return 0;
}