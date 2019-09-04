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
struct ubi_attach_info {int dummy; } ;
struct ubi_ainf_volume {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AV_ADD ; 
 struct ubi_ainf_volume* find_or_add_av (struct ubi_attach_info*,int,int /*<<< orphan*/ ,int*) ; 

struct ubi_ainf_volume *ubi_add_av(struct ubi_attach_info *ai, int vol_id)
{
	bool created;

	return find_or_add_av(ai, vol_id, AV_ADD, &created);
}