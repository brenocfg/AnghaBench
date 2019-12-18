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
typedef  int /*<<< orphan*/  u32 ;
struct sas_identify_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mvs_94xx_make_dev_info (struct sas_identify_frame*) ; 

__attribute__((used)) static u32 mvs_94xx_make_att_info(struct sas_identify_frame *id)
{
	return mvs_94xx_make_dev_info(id);
}