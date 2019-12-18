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
typedef  int u16 ;
struct country_code_to_enum_rd {int dummy; } ;

/* Variables and functions */
 int COUNTRY_ERD_FLAG ; 
 int CTRY_DEFAULT ; 
 struct country_code_to_enum_rd* ath_regd_find_country (int) ; 

__attribute__((used)) static u16 ath_regd_get_default_country(u16 rd)
{
	if (rd & COUNTRY_ERD_FLAG) {
		struct country_code_to_enum_rd *country = NULL;
		u16 cc = rd & ~COUNTRY_ERD_FLAG;

		country = ath_regd_find_country(cc);
		if (country != NULL)
			return cc;
	}

	return CTRY_DEFAULT;
}