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
struct nlattr {int dummy; } ;

/* Variables and functions */
 size_t MACSEC_RXSC_ATTR_ACTIVE ; 
 size_t MACSEC_RXSC_ATTR_SCI ; 
 int nla_get_u8 (struct nlattr*) ; 

__attribute__((used)) static bool validate_add_rxsc(struct nlattr **attrs)
{
	if (!attrs[MACSEC_RXSC_ATTR_SCI])
		return false;

	if (attrs[MACSEC_RXSC_ATTR_ACTIVE]) {
		if (nla_get_u8(attrs[MACSEC_RXSC_ATTR_ACTIVE]) > 1)
			return false;
	}

	return true;
}