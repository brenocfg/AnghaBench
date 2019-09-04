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

/* Variables and functions */
#define  MLX 132 
 int MTHCA_QP_ST_MLX ; 
 int MTHCA_QP_ST_RC ; 
 int MTHCA_QP_ST_RD ; 
 int MTHCA_QP_ST_UC ; 
 int MTHCA_QP_ST_UD ; 
#define  RC 131 
#define  RD 130 
#define  UC 129 
#define  UD 128 

__attribute__((used)) static int to_mthca_st(int transport)
{
	switch (transport) {
	case RC:  return MTHCA_QP_ST_RC;
	case UC:  return MTHCA_QP_ST_UC;
	case UD:  return MTHCA_QP_ST_UD;
	case RD:  return MTHCA_QP_ST_RD;
	case MLX: return MTHCA_QP_ST_MLX;
	default:  return -1;
	}
}