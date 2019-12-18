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
typedef  enum spi_nor_protocol { ____Placeholder_spi_nor_protocol } spi_nor_protocol ;
typedef  enum hifmc_iftype { ____Placeholder_hifmc_iftype } hifmc_iftype ;

/* Variables and functions */
 int IF_TYPE_DIO ; 
 int IF_TYPE_DUAL ; 
 int IF_TYPE_QIO ; 
 int IF_TYPE_QUAD ; 
 int IF_TYPE_STD ; 
#define  SNOR_PROTO_1_1_1 132 
#define  SNOR_PROTO_1_1_2 131 
#define  SNOR_PROTO_1_1_4 130 
#define  SNOR_PROTO_1_2_2 129 
#define  SNOR_PROTO_1_4_4 128 

__attribute__((used)) static int hisi_spi_nor_get_if_type(enum spi_nor_protocol proto)
{
	enum hifmc_iftype if_type;

	switch (proto) {
	case SNOR_PROTO_1_1_2:
		if_type = IF_TYPE_DUAL;
		break;
	case SNOR_PROTO_1_2_2:
		if_type = IF_TYPE_DIO;
		break;
	case SNOR_PROTO_1_1_4:
		if_type = IF_TYPE_QUAD;
		break;
	case SNOR_PROTO_1_4_4:
		if_type = IF_TYPE_QIO;
		break;
	case SNOR_PROTO_1_1_1:
	default:
		if_type = IF_TYPE_STD;
		break;
	}

	return if_type;
}