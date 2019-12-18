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
struct nxp_fspi {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 

__attribute__((used)) static int nxp_fspi_check_buswidth(struct nxp_fspi *f, u8 width)
{
	switch (width) {
	case 1:
	case 2:
	case 4:
	case 8:
		return 0;
	}

	return -ENOTSUPP;
}