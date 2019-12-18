#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct seq_file {struct adapter* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__*) ; 
 int CIM_NUM_IBQ ; 
 int CIM_NUM_OBQ ; 
 int CIM_NUM_OBQ_T5 ; 
 int /*<<< orphan*/  IBQRDADDR_G (scalar_t__) ; 
 int /*<<< orphan*/  IBQWRADDR_G (scalar_t__) ; 
 int /*<<< orphan*/  QUEEOPCNT_G (scalar_t__) ; 
 int QUERDADDR_G (scalar_t__) ; 
 int QUEREMFLITS_G (scalar_t__) ; 
 int /*<<< orphan*/  QUESOPCNT_G (scalar_t__) ; 
 int /*<<< orphan*/  UP_IBQ_0_RDADDR_A ; 
 int /*<<< orphan*/  UP_IBQ_0_SHADOW_RDADDR_A ; 
 int /*<<< orphan*/  UP_OBQ_0_REALADDR_A ; 
 int /*<<< orphan*/  UP_OBQ_0_SHADOW_REALADDR_A ; 
 scalar_t__ is_t4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int t4_cim_read (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  t4_read_cimq_cfg (struct adapter*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int cim_qcfg_show(struct seq_file *seq, void *v)
{
	static const char * const qname[] = {
		"TP0", "TP1", "ULP", "SGE0", "SGE1", "NC-SI",
		"ULP0", "ULP1", "ULP2", "ULP3", "SGE", "NC-SI",
		"SGE0-RX", "SGE1-RX"
	};

	int i;
	struct adapter *adap = seq->private;
	u16 base[CIM_NUM_IBQ + CIM_NUM_OBQ_T5];
	u16 size[CIM_NUM_IBQ + CIM_NUM_OBQ_T5];
	u32 stat[(4 * (CIM_NUM_IBQ + CIM_NUM_OBQ_T5))];
	u16 thres[CIM_NUM_IBQ];
	u32 obq_wr_t4[2 * CIM_NUM_OBQ], *wr;
	u32 obq_wr_t5[2 * CIM_NUM_OBQ_T5];
	u32 *p = stat;
	int cim_num_obq = is_t4(adap->params.chip) ?
				CIM_NUM_OBQ : CIM_NUM_OBQ_T5;

	i = t4_cim_read(adap, is_t4(adap->params.chip) ? UP_IBQ_0_RDADDR_A :
			UP_IBQ_0_SHADOW_RDADDR_A,
			ARRAY_SIZE(stat), stat);
	if (!i) {
		if (is_t4(adap->params.chip)) {
			i = t4_cim_read(adap, UP_OBQ_0_REALADDR_A,
					ARRAY_SIZE(obq_wr_t4), obq_wr_t4);
			wr = obq_wr_t4;
		} else {
			i = t4_cim_read(adap, UP_OBQ_0_SHADOW_REALADDR_A,
					ARRAY_SIZE(obq_wr_t5), obq_wr_t5);
			wr = obq_wr_t5;
		}
	}
	if (i)
		return i;

	t4_read_cimq_cfg(adap, base, size, thres);

	seq_printf(seq,
		   "  Queue  Base  Size Thres  RdPtr WrPtr  SOP  EOP Avail\n");
	for (i = 0; i < CIM_NUM_IBQ; i++, p += 4)
		seq_printf(seq, "%7s %5x %5u %5u %6x  %4x %4u %4u %5u\n",
			   qname[i], base[i], size[i], thres[i],
			   IBQRDADDR_G(p[0]), IBQWRADDR_G(p[1]),
			   QUESOPCNT_G(p[3]), QUEEOPCNT_G(p[3]),
			   QUEREMFLITS_G(p[2]) * 16);
	for ( ; i < CIM_NUM_IBQ + cim_num_obq; i++, p += 4, wr += 2)
		seq_printf(seq, "%7s %5x %5u %12x  %4x %4u %4u %5u\n",
			   qname[i], base[i], size[i],
			   QUERDADDR_G(p[0]) & 0x3fff, wr[0] - base[i],
			   QUESOPCNT_G(p[3]), QUEEOPCNT_G(p[3]),
			   QUEREMFLITS_G(p[2]) * 16);
	return 0;
}