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

/* Variables and functions */
#define  MLX5_HEALTH_SYNDR_ASYNC_EQ_OVERRUN_ERR 138 
#define  MLX5_HEALTH_SYNDR_CRC_ERR 137 
#define  MLX5_HEALTH_SYNDR_EQ_ERR 136 
#define  MLX5_HEALTH_SYNDR_EQ_INV 135 
#define  MLX5_HEALTH_SYNDR_FETCH_PCI_ERR 134 
#define  MLX5_HEALTH_SYNDR_FFSER_ERR 133 
#define  MLX5_HEALTH_SYNDR_FW_ERR 132 
#define  MLX5_HEALTH_SYNDR_HIGH_TEMP 131 
#define  MLX5_HEALTH_SYNDR_HW_FTL_ERR 130 
#define  MLX5_HEALTH_SYNDR_HW_UNRECOVERABLE_ERR 129 
#define  MLX5_HEALTH_SYNDR_IRISC_ERR 128 

__attribute__((used)) static const char *hsynd_str(u8 synd)
{
	switch (synd) {
	case MLX5_HEALTH_SYNDR_FW_ERR:
		return "firmware internal error";
	case MLX5_HEALTH_SYNDR_IRISC_ERR:
		return "irisc not responding";
	case MLX5_HEALTH_SYNDR_HW_UNRECOVERABLE_ERR:
		return "unrecoverable hardware error";
	case MLX5_HEALTH_SYNDR_CRC_ERR:
		return "firmware CRC error";
	case MLX5_HEALTH_SYNDR_FETCH_PCI_ERR:
		return "ICM fetch PCI error";
	case MLX5_HEALTH_SYNDR_HW_FTL_ERR:
		return "HW fatal error\n";
	case MLX5_HEALTH_SYNDR_ASYNC_EQ_OVERRUN_ERR:
		return "async EQ buffer overrun";
	case MLX5_HEALTH_SYNDR_EQ_ERR:
		return "EQ error";
	case MLX5_HEALTH_SYNDR_EQ_INV:
		return "Invalid EQ referenced";
	case MLX5_HEALTH_SYNDR_FFSER_ERR:
		return "FFSER error";
	case MLX5_HEALTH_SYNDR_HIGH_TEMP:
		return "High temperature";
	default:
		return "unrecognized error";
	}
}