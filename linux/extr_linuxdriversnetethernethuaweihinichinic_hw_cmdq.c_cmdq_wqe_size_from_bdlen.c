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
typedef  enum bufdesc_len { ____Placeholder_bufdesc_len } bufdesc_len ;

/* Variables and functions */
#define  BUFDESC_LCMD_LEN 129 
#define  BUFDESC_SCMD_LEN 128 
 unsigned int WQE_LCMD_SIZE ; 
 unsigned int WQE_SCMD_SIZE ; 

__attribute__((used)) static unsigned int cmdq_wqe_size_from_bdlen(enum bufdesc_len len)
{
	unsigned int wqe_size = 0;

	switch (len) {
	case BUFDESC_LCMD_LEN:
		wqe_size = WQE_LCMD_SIZE;
		break;
	case BUFDESC_SCMD_LEN:
		wqe_size = WQE_SCMD_SIZE;
		break;
	}

	return wqe_size;
}