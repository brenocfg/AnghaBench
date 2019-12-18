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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  CODA_7541 131 
#define  CODA_960 130 
#define  CODA_DX6 129 
#define  CODA_HX4 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

const char *coda_product_name(int product)
{
	static char buf[9];

	switch (product) {
	case CODA_DX6:
		return "CodaDx6";
	case CODA_HX4:
		return "CodaHx4";
	case CODA_7541:
		return "CODA7541";
	case CODA_960:
		return "CODA960";
	default:
		snprintf(buf, sizeof(buf), "(0x%04x)", product);
		return buf;
	}
}