#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct iwl_trans {int dummy; } ;
struct TYPE_3__ {int log_event_table; } ;
struct iwl_priv {scalar_t__ cur_ucode; TYPE_2__* fw; TYPE_1__ device_pointers; struct iwl_trans* trans; } ;
struct TYPE_4__ {int init_evtlog_size; int init_evtlog_ptr; int inst_evtlog_size; int inst_evtlog_ptr; } ;

/* Variables and functions */
 int DEFAULT_DUMP_EVENT_LOG_ENTRIES ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IWL_DL_FW ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*,...) ; 
 scalar_t__ IWL_UCODE_INIT ; 
 scalar_t__ iwl_have_debug_level (int /*<<< orphan*/ ) ; 
 int iwl_print_event_log (struct iwl_priv*,int,int,int,int,char**,size_t) ; 
 int iwl_print_last_event_logs (struct iwl_priv*,int,int,int,int,int,int,char**,size_t) ; 
 int iwl_trans_read_mem32 (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwlagn_hw_valid_rtc_data_addr (int) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 

int iwl_dump_nic_event_log(struct iwl_priv *priv, bool full_log,
			    char **buf)
{
	u32 base;       /* SRAM byte address of event log header */
	u32 capacity;   /* event log capacity in # entries */
	u32 mode;       /* 0 - no timestamp, 1 - timestamp recorded */
	u32 num_wraps;  /* # times uCode wrapped to top of log */
	u32 next_entry; /* index of next entry to be written by uCode */
	u32 size;       /* # entries that we'll print */
	u32 logsize;
	int pos = 0;
	size_t bufsz = 0;
	struct iwl_trans *trans = priv->trans;

	base = priv->device_pointers.log_event_table;
	if (priv->cur_ucode == IWL_UCODE_INIT) {
		logsize = priv->fw->init_evtlog_size;
		if (!base)
			base = priv->fw->init_evtlog_ptr;
	} else {
		logsize = priv->fw->inst_evtlog_size;
		if (!base)
			base = priv->fw->inst_evtlog_ptr;
	}

	if (!iwlagn_hw_valid_rtc_data_addr(base)) {
		IWL_ERR(priv,
			"Invalid event log pointer 0x%08X for %s uCode\n",
			base,
			(priv->cur_ucode == IWL_UCODE_INIT)
					? "Init" : "RT");
		return -EINVAL;
	}

	/* event log header */
	capacity = iwl_trans_read_mem32(trans, base);
	mode = iwl_trans_read_mem32(trans, base + (1 * sizeof(u32)));
	num_wraps = iwl_trans_read_mem32(trans, base + (2 * sizeof(u32)));
	next_entry = iwl_trans_read_mem32(trans, base + (3 * sizeof(u32)));

	if (capacity > logsize) {
		IWL_ERR(priv, "Log capacity %d is bogus, limit to %d "
			"entries\n", capacity, logsize);
		capacity = logsize;
	}

	if (next_entry > logsize) {
		IWL_ERR(priv, "Log write index %d is bogus, limit to %d\n",
			next_entry, logsize);
		next_entry = logsize;
	}

	size = num_wraps ? capacity : next_entry;

	/* bail out if nothing in log */
	if (size == 0) {
		IWL_ERR(trans, "Start IWL Event Log Dump: nothing in log\n");
		return pos;
	}

	if (!(iwl_have_debug_level(IWL_DL_FW)) && !full_log)
		size = (size > DEFAULT_DUMP_EVENT_LOG_ENTRIES)
			? DEFAULT_DUMP_EVENT_LOG_ENTRIES : size;
	IWL_ERR(priv, "Start IWL Event Log Dump: display last %u entries\n",
		size);

#ifdef CONFIG_IWLWIFI_DEBUG
	if (buf) {
		if (full_log)
			bufsz = capacity * 48;
		else
			bufsz = size * 48;
		*buf = kmalloc(bufsz, GFP_KERNEL);
		if (!*buf)
			return -ENOMEM;
	}
	if (iwl_have_debug_level(IWL_DL_FW) || full_log) {
		/*
		 * if uCode has wrapped back to top of log,
		 * start at the oldest entry,
		 * i.e the next one that uCode would fill.
		 */
		if (num_wraps)
			pos = iwl_print_event_log(priv, next_entry,
						capacity - next_entry, mode,
						pos, buf, bufsz);
		/* (then/else) start at top of log */
		pos = iwl_print_event_log(priv, 0,
					  next_entry, mode, pos, buf, bufsz);
	} else
		pos = iwl_print_last_event_logs(priv, capacity, num_wraps,
						next_entry, size, mode,
						pos, buf, bufsz);
#else
	pos = iwl_print_last_event_logs(priv, capacity, num_wraps,
					next_entry, size, mode,
					pos, buf, bufsz);
#endif
	return pos;
}