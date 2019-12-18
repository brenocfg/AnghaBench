#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int regshift; scalar_t__ membase; } ;
struct uart_omap_port {int errata; int /*<<< orphan*/  features; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; TYPE_1__ port; } ;

/* Variables and functions */
 int OMAP_UART_LEGACY_MVR_MAJ_MASK ; 
 int OMAP_UART_LEGACY_MVR_MAJ_SHIFT ; 
 int OMAP_UART_LEGACY_MVR_MIN_MASK ; 
 int OMAP_UART_MVR_MAJ_MASK ; 
 int OMAP_UART_MVR_MAJ_SHIFT ; 
 int OMAP_UART_MVR_MIN_MASK ; 
 int OMAP_UART_MVR_SCHEME_SHIFT ; 
#define  OMAP_UART_REV_46 130 
#define  OMAP_UART_REV_52 129 
#define  OMAP_UART_REV_63 128 
 int /*<<< orphan*/  OMAP_UART_WER_HAS_TX_WAKEUP ; 
 int UART_BUILD_REVISION (int,int) ; 
 int UART_ERRATA_i202_MDR1_ACCESS ; 
 int UART_ERRATA_i291_DMA_FORCEIDLE ; 
 int UART_OMAP_MVER ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void omap_serial_fill_features_erratas(struct uart_omap_port *up)
{
	u32 mvr, scheme;
	u16 revision, major, minor;

	mvr = readl(up->port.membase + (UART_OMAP_MVER << up->port.regshift));

	/* Check revision register scheme */
	scheme = mvr >> OMAP_UART_MVR_SCHEME_SHIFT;

	switch (scheme) {
	case 0: /* Legacy Scheme: OMAP2/3 */
		/* MINOR_REV[0:4], MAJOR_REV[4:7] */
		major = (mvr & OMAP_UART_LEGACY_MVR_MAJ_MASK) >>
					OMAP_UART_LEGACY_MVR_MAJ_SHIFT;
		minor = (mvr & OMAP_UART_LEGACY_MVR_MIN_MASK);
		break;
	case 1:
		/* New Scheme: OMAP4+ */
		/* MINOR_REV[0:5], MAJOR_REV[8:10] */
		major = (mvr & OMAP_UART_MVR_MAJ_MASK) >>
					OMAP_UART_MVR_MAJ_SHIFT;
		minor = (mvr & OMAP_UART_MVR_MIN_MASK);
		break;
	default:
		dev_warn(up->dev,
			"Unknown %s revision, defaulting to highest\n",
			up->name);
		/* highest possible revision */
		major = 0xff;
		minor = 0xff;
	}

	/* normalize revision for the driver */
	revision = UART_BUILD_REVISION(major, minor);

	switch (revision) {
	case OMAP_UART_REV_46:
		up->errata |= (UART_ERRATA_i202_MDR1_ACCESS |
				UART_ERRATA_i291_DMA_FORCEIDLE);
		break;
	case OMAP_UART_REV_52:
		up->errata |= (UART_ERRATA_i202_MDR1_ACCESS |
				UART_ERRATA_i291_DMA_FORCEIDLE);
		up->features |= OMAP_UART_WER_HAS_TX_WAKEUP;
		break;
	case OMAP_UART_REV_63:
		up->errata |= UART_ERRATA_i202_MDR1_ACCESS;
		up->features |= OMAP_UART_WER_HAS_TX_WAKEUP;
		break;
	default:
		break;
	}
}