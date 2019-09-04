#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {size_t link_error_type; int /*<<< orphan*/  effective_address; int /*<<< orphan*/  effective_address_provided; } ;
struct TYPE_15__ {size_t ra_error_type; int /*<<< orphan*/  effective_address; int /*<<< orphan*/  effective_address_provided; } ;
struct TYPE_14__ {size_t user_error_type; int /*<<< orphan*/  effective_address; int /*<<< orphan*/  effective_address_provided; } ;
struct TYPE_13__ {size_t tlb_error_type; int /*<<< orphan*/  effective_address; int /*<<< orphan*/  effective_address_provided; } ;
struct TYPE_12__ {size_t erat_error_type; int /*<<< orphan*/  effective_address; int /*<<< orphan*/  effective_address_provided; } ;
struct TYPE_11__ {size_t slb_error_type; int /*<<< orphan*/  effective_address; int /*<<< orphan*/  effective_address_provided; } ;
struct TYPE_10__ {size_t ue_error_type; int /*<<< orphan*/  physical_address; int /*<<< orphan*/  physical_address_provided; int /*<<< orphan*/  effective_address; int /*<<< orphan*/  effective_address_provided; } ;
struct TYPE_17__ {TYPE_7__ link_error; TYPE_6__ ra_error; TYPE_5__ user_error; TYPE_4__ tlb_error; TYPE_3__ erat_error; TYPE_2__ slb_error; TYPE_1__ ue_error; } ;
struct machine_check_event {scalar_t__ version; int severity; scalar_t__ disposition; scalar_t__ initiator; int error_type; TYPE_8__ u; scalar_t__ srr0; } ;
struct TYPE_18__ {int /*<<< orphan*/  comm; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const**) ; 
 char* KERN_ERR ; 
 char* KERN_INFO ; 
 char* KERN_WARNING ; 
 scalar_t__ MCE_DISPOSITION_RECOVERED ; 
#define  MCE_ERROR_TYPE_ERAT 139 
#define  MCE_ERROR_TYPE_LINK 138 
#define  MCE_ERROR_TYPE_RA 137 
#define  MCE_ERROR_TYPE_SLB 136 
#define  MCE_ERROR_TYPE_TLB 135 
#define  MCE_ERROR_TYPE_UE 134 
#define  MCE_ERROR_TYPE_UNKNOWN 133 
#define  MCE_ERROR_TYPE_USER 132 
 scalar_t__ MCE_INITIATOR_CPU ; 
#define  MCE_SEV_ERROR_SYNC 131 
#define  MCE_SEV_FATAL 130 
#define  MCE_SEV_NO_ERROR 129 
#define  MCE_SEV_WARNING 128 
 scalar_t__ MCE_V1 ; 
 TYPE_9__* current ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,char const*,...) ; 

void machine_check_print_event_info(struct machine_check_event *evt,
				    bool user_mode)
{
	const char *level, *sevstr, *subtype;
	static const char *mc_ue_types[] = {
		"Indeterminate",
		"Instruction fetch",
		"Page table walk ifetch",
		"Load/Store",
		"Page table walk Load/Store",
	};
	static const char *mc_slb_types[] = {
		"Indeterminate",
		"Parity",
		"Multihit",
	};
	static const char *mc_erat_types[] = {
		"Indeterminate",
		"Parity",
		"Multihit",
	};
	static const char *mc_tlb_types[] = {
		"Indeterminate",
		"Parity",
		"Multihit",
	};
	static const char *mc_user_types[] = {
		"Indeterminate",
		"tlbie(l) invalid",
	};
	static const char *mc_ra_types[] = {
		"Indeterminate",
		"Instruction fetch (bad)",
		"Instruction fetch (foreign)",
		"Page table walk ifetch (bad)",
		"Page table walk ifetch (foreign)",
		"Load (bad)",
		"Store (bad)",
		"Page table walk Load/Store (bad)",
		"Page table walk Load/Store (foreign)",
		"Load/Store (foreign)",
	};
	static const char *mc_link_types[] = {
		"Indeterminate",
		"Instruction fetch (timeout)",
		"Page table walk ifetch (timeout)",
		"Load (timeout)",
		"Store (timeout)",
		"Page table walk Load/Store (timeout)",
	};

	/* Print things out */
	if (evt->version != MCE_V1) {
		pr_err("Machine Check Exception, Unknown event version %d !\n",
		       evt->version);
		return;
	}
	switch (evt->severity) {
	case MCE_SEV_NO_ERROR:
		level = KERN_INFO;
		sevstr = "Harmless";
		break;
	case MCE_SEV_WARNING:
		level = KERN_WARNING;
		sevstr = "";
		break;
	case MCE_SEV_ERROR_SYNC:
		level = KERN_ERR;
		sevstr = "Severe";
		break;
	case MCE_SEV_FATAL:
	default:
		level = KERN_ERR;
		sevstr = "Fatal";
		break;
	}

	printk("%s%s Machine check interrupt [%s]\n", level, sevstr,
	       evt->disposition == MCE_DISPOSITION_RECOVERED ?
	       "Recovered" : "Not recovered");

	if (user_mode) {
		printk("%s  NIP: [%016llx] PID: %d Comm: %s\n", level,
			evt->srr0, current->pid, current->comm);
	} else {
		printk("%s  NIP [%016llx]: %pS\n", level, evt->srr0,
		       (void *)evt->srr0);
	}

	printk("%s  Initiator: %s\n", level,
	       evt->initiator == MCE_INITIATOR_CPU ? "CPU" : "Unknown");
	switch (evt->error_type) {
	case MCE_ERROR_TYPE_UE:
		subtype = evt->u.ue_error.ue_error_type <
			ARRAY_SIZE(mc_ue_types) ?
			mc_ue_types[evt->u.ue_error.ue_error_type]
			: "Unknown";
		printk("%s  Error type: UE [%s]\n", level, subtype);
		if (evt->u.ue_error.effective_address_provided)
			printk("%s    Effective address: %016llx\n",
			       level, evt->u.ue_error.effective_address);
		if (evt->u.ue_error.physical_address_provided)
			printk("%s    Physical address:  %016llx\n",
			       level, evt->u.ue_error.physical_address);
		break;
	case MCE_ERROR_TYPE_SLB:
		subtype = evt->u.slb_error.slb_error_type <
			ARRAY_SIZE(mc_slb_types) ?
			mc_slb_types[evt->u.slb_error.slb_error_type]
			: "Unknown";
		printk("%s  Error type: SLB [%s]\n", level, subtype);
		if (evt->u.slb_error.effective_address_provided)
			printk("%s    Effective address: %016llx\n",
			       level, evt->u.slb_error.effective_address);
		break;
	case MCE_ERROR_TYPE_ERAT:
		subtype = evt->u.erat_error.erat_error_type <
			ARRAY_SIZE(mc_erat_types) ?
			mc_erat_types[evt->u.erat_error.erat_error_type]
			: "Unknown";
		printk("%s  Error type: ERAT [%s]\n", level, subtype);
		if (evt->u.erat_error.effective_address_provided)
			printk("%s    Effective address: %016llx\n",
			       level, evt->u.erat_error.effective_address);
		break;
	case MCE_ERROR_TYPE_TLB:
		subtype = evt->u.tlb_error.tlb_error_type <
			ARRAY_SIZE(mc_tlb_types) ?
			mc_tlb_types[evt->u.tlb_error.tlb_error_type]
			: "Unknown";
		printk("%s  Error type: TLB [%s]\n", level, subtype);
		if (evt->u.tlb_error.effective_address_provided)
			printk("%s    Effective address: %016llx\n",
			       level, evt->u.tlb_error.effective_address);
		break;
	case MCE_ERROR_TYPE_USER:
		subtype = evt->u.user_error.user_error_type <
			ARRAY_SIZE(mc_user_types) ?
			mc_user_types[evt->u.user_error.user_error_type]
			: "Unknown";
		printk("%s  Error type: User [%s]\n", level, subtype);
		if (evt->u.user_error.effective_address_provided)
			printk("%s    Effective address: %016llx\n",
			       level, evt->u.user_error.effective_address);
		break;
	case MCE_ERROR_TYPE_RA:
		subtype = evt->u.ra_error.ra_error_type <
			ARRAY_SIZE(mc_ra_types) ?
			mc_ra_types[evt->u.ra_error.ra_error_type]
			: "Unknown";
		printk("%s  Error type: Real address [%s]\n", level, subtype);
		if (evt->u.ra_error.effective_address_provided)
			printk("%s    Effective address: %016llx\n",
			       level, evt->u.ra_error.effective_address);
		break;
	case MCE_ERROR_TYPE_LINK:
		subtype = evt->u.link_error.link_error_type <
			ARRAY_SIZE(mc_link_types) ?
			mc_link_types[evt->u.link_error.link_error_type]
			: "Unknown";
		printk("%s  Error type: Link [%s]\n", level, subtype);
		if (evt->u.link_error.effective_address_provided)
			printk("%s    Effective address: %016llx\n",
			       level, evt->u.link_error.effective_address);
		break;
	default:
	case MCE_ERROR_TYPE_UNKNOWN:
		printk("%s  Error type: Unknown\n", level);
		break;
	}
}