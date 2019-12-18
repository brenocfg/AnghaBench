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
typedef  int u8 ;
typedef  int u16 ;
struct asd_ha_struct {int dummy; } ;

/* Variables and functions */
 int asd_scbsite_read_word (struct asd_ha_struct*,int,int) ; 

__attribute__((used)) static inline u8 asd_scbsite_read_byte(struct asd_ha_struct *asd_ha,
				       u16 scb_site_no,
				       u16 offs)
{
	if (offs & 1)
		return asd_scbsite_read_word(asd_ha, scb_site_no,
					     offs & ~1) >> 8;
	else
		return asd_scbsite_read_word(asd_ha, scb_site_no,
					     offs) & 0xFF;
}