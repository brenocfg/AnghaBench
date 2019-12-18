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
struct iss_ipipeif_device {int dummy; } ;
struct iss_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CADL ; 
 int /*<<< orphan*/  CADU ; 
 int /*<<< orphan*/  CCOLP ; 
 int /*<<< orphan*/  CFG1 ; 
 int /*<<< orphan*/  CFG2 ; 
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  HSIZE ; 
 int /*<<< orphan*/  IPIPEIF_PRINT_REGISTER (struct iss_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQENABLE_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQENABLE_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQSTATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISIF_PRINT_REGISTER (struct iss_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP5_PRINT_REGISTER (struct iss_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LNH ; 
 int /*<<< orphan*/  LNV ; 
 int /*<<< orphan*/  MODESET ; 
 int /*<<< orphan*/  SPH ; 
 int /*<<< orphan*/  SYNCEN ; 
 int /*<<< orphan*/  SYSCONFIG ; 
 int /*<<< orphan*/  VDINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct iss_device* to_iss_device (struct iss_ipipeif_device*) ; 

__attribute__((used)) static void ipipeif_print_status(struct iss_ipipeif_device *ipipeif)
{
	struct iss_device *iss = to_iss_device(ipipeif);

	dev_dbg(iss->dev, "-------------IPIPEIF Register dump-------------\n");

	IPIPEIF_PRINT_REGISTER(iss, CFG1);
	IPIPEIF_PRINT_REGISTER(iss, CFG2);

	ISIF_PRINT_REGISTER(iss, SYNCEN);
	ISIF_PRINT_REGISTER(iss, CADU);
	ISIF_PRINT_REGISTER(iss, CADL);
	ISIF_PRINT_REGISTER(iss, MODESET);
	ISIF_PRINT_REGISTER(iss, CCOLP);
	ISIF_PRINT_REGISTER(iss, SPH);
	ISIF_PRINT_REGISTER(iss, LNH);
	ISIF_PRINT_REGISTER(iss, LNV);
	ISIF_PRINT_REGISTER(iss, VDINT(0));
	ISIF_PRINT_REGISTER(iss, HSIZE);

	ISP5_PRINT_REGISTER(iss, SYSCONFIG);
	ISP5_PRINT_REGISTER(iss, CTRL);
	ISP5_PRINT_REGISTER(iss, IRQSTATUS(0));
	ISP5_PRINT_REGISTER(iss, IRQENABLE_SET(0));
	ISP5_PRINT_REGISTER(iss, IRQENABLE_CLR(0));

	dev_dbg(iss->dev, "-----------------------------------------------\n");
}