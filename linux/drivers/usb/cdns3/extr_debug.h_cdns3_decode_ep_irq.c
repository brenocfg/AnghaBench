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
typedef  int u32 ;

/* Variables and functions */
 int EP_STS_DESCMIS ; 
 int EP_STS_IOC ; 
 int EP_STS_IOT ; 
 int EP_STS_ISOERR ; 
 int EP_STS_ISP ; 
 int EP_STS_MD_EXIT ; 
 int EP_STS_NRDY ; 
 int EP_STS_OUTSMM ; 
 int EP_STS_PRIME ; 
 int EP_STS_SETUP ; 
 int EP_STS_SIDERR ; 
 int EP_STS_STREAMR ; 
 int EP_STS_TRBERR ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static inline  char *cdns3_decode_ep_irq(char *str,
					 u32 ep_sts,
					 const char *ep_name)
{
	int ret;

	ret = sprintf(str, "IRQ for %s: %08x ", ep_name, ep_sts);

	if (ep_sts & EP_STS_SETUP)
		ret += sprintf(str + ret, "SETUP ");
	if (ep_sts & EP_STS_IOC)
		ret += sprintf(str + ret, "IOC ");
	if (ep_sts & EP_STS_ISP)
		ret += sprintf(str + ret, "ISP ");
	if (ep_sts & EP_STS_DESCMIS)
		ret += sprintf(str + ret, "DESCMIS ");
	if (ep_sts & EP_STS_STREAMR)
		ret += sprintf(str + ret, "STREAMR ");
	if (ep_sts & EP_STS_MD_EXIT)
		ret += sprintf(str + ret, "MD_EXIT ");
	if (ep_sts & EP_STS_TRBERR)
		ret += sprintf(str + ret, "TRBERR ");
	if (ep_sts & EP_STS_NRDY)
		ret += sprintf(str + ret, "NRDY ");
	if (ep_sts & EP_STS_PRIME)
		ret += sprintf(str + ret, "PRIME ");
	if (ep_sts & EP_STS_SIDERR)
		ret += sprintf(str + ret, "SIDERRT ");
	if (ep_sts & EP_STS_OUTSMM)
		ret += sprintf(str + ret, "OUTSMM ");
	if (ep_sts & EP_STS_ISOERR)
		ret += sprintf(str + ret, "ISOERR ");
	if (ep_sts & EP_STS_IOT)
		ret += sprintf(str + ret, "IOT ");

	return str;
}