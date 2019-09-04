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
typedef  enum mlx5_ifc_fpga_ipsec_response_syndrome { ____Placeholder_mlx5_ifc_fpga_ipsec_response_syndrome } mlx5_ifc_fpga_ipsec_response_syndrome ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int EIO ; 
#define  MLX5_FPGA_IPSEC_RESPONSE_ILLEGAL_REQUEST 131 
#define  MLX5_FPGA_IPSEC_RESPONSE_SADB_ISSUE 130 
#define  MLX5_FPGA_IPSEC_RESPONSE_SUCCESS 129 
#define  MLX5_FPGA_IPSEC_RESPONSE_WRITE_RESPONSE_ISSUE 128 

__attribute__((used)) static inline
int syndrome_to_errno(enum mlx5_ifc_fpga_ipsec_response_syndrome syndrome)
{
	switch (syndrome) {
	case MLX5_FPGA_IPSEC_RESPONSE_SUCCESS:
		return 0;
	case MLX5_FPGA_IPSEC_RESPONSE_SADB_ISSUE:
		return -EEXIST;
	case MLX5_FPGA_IPSEC_RESPONSE_ILLEGAL_REQUEST:
		return -EINVAL;
	case MLX5_FPGA_IPSEC_RESPONSE_WRITE_RESPONSE_ISSUE:
		return -EIO;
	}
	return -EIO;
}