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
struct file {int dummy; } ;

/* Variables and functions */
 int EBADRQC ; 
#define  GRU_CREATE_CONTEXT 137 
#define  GRU_DUMP_CHIPLET_STATE 136 
#define  GRU_GET_CONFIG_INFO 135 
#define  GRU_GET_GSEG_STATISTICS 134 
#define  GRU_KTEST 133 
#define  GRU_SET_CONTEXT_OPTION 132 
#define  GRU_USER_CALL_OS 131 
#define  GRU_USER_FLUSH_TLB 130 
#define  GRU_USER_GET_EXCEPTION_DETAIL 129 
#define  GRU_USER_UNLOAD_CONTEXT 128 
 int gru_create_new_context (unsigned long) ; 
 int /*<<< orphan*/  gru_dbg (int /*<<< orphan*/ ,char*,struct file*,unsigned int,unsigned long) ; 
 int gru_dump_chiplet_request (unsigned long) ; 
 int gru_get_config_info (unsigned long) ; 
 int gru_get_exception_detail (unsigned long) ; 
 int gru_get_gseg_statistics (unsigned long) ; 
 int gru_handle_user_call_os (unsigned long) ; 
 int gru_ktest (unsigned long) ; 
 int gru_set_context_option (unsigned long) ; 
 int gru_user_flush_tlb (unsigned long) ; 
 int gru_user_unload_context (unsigned long) ; 
 int /*<<< orphan*/  grudev ; 

__attribute__((used)) static long gru_file_unlocked_ioctl(struct file *file, unsigned int req,
				    unsigned long arg)
{
	int err = -EBADRQC;

	gru_dbg(grudev, "file %p, req 0x%x, 0x%lx\n", file, req, arg);

	switch (req) {
	case GRU_CREATE_CONTEXT:
		err = gru_create_new_context(arg);
		break;
	case GRU_SET_CONTEXT_OPTION:
		err = gru_set_context_option(arg);
		break;
	case GRU_USER_GET_EXCEPTION_DETAIL:
		err = gru_get_exception_detail(arg);
		break;
	case GRU_USER_UNLOAD_CONTEXT:
		err = gru_user_unload_context(arg);
		break;
	case GRU_USER_FLUSH_TLB:
		err = gru_user_flush_tlb(arg);
		break;
	case GRU_USER_CALL_OS:
		err = gru_handle_user_call_os(arg);
		break;
	case GRU_GET_GSEG_STATISTICS:
		err = gru_get_gseg_statistics(arg);
		break;
	case GRU_KTEST:
		err = gru_ktest(arg);
		break;
	case GRU_GET_CONFIG_INFO:
		err = gru_get_config_info(arg);
		break;
	case GRU_DUMP_CHIPLET_STATE:
		err = gru_dump_chiplet_request(arg);
		break;
	}
	return err;
}