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

/* Variables and functions */
 int SNIC_TGT_NONE ; 
 int SNIC_TGT_SAN ; 
 char const** snic_tgt_type_str ; 

__attribute__((used)) static inline const char *
snic_tgt_type_to_str(int typ)
{
	return ((typ > SNIC_TGT_NONE && typ <= SNIC_TGT_SAN) ?
		 snic_tgt_type_str[typ] : "Unknown");
}