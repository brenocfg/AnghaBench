#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ set_uuid0; scalar_t__ set_uuid1; scalar_t__ set_uuid2; scalar_t__ set_uuid3; } ;
typedef  TYPE_1__ mdp_super_t ;

/* Variables and functions */

__attribute__((used)) static int md_uuid_equal(mdp_super_t *sb1, mdp_super_t *sb2)
{
	return	sb1->set_uuid0 == sb2->set_uuid0 &&
		sb1->set_uuid1 == sb2->set_uuid1 &&
		sb1->set_uuid2 == sb2->set_uuid2 &&
		sb1->set_uuid3 == sb2->set_uuid3;
}