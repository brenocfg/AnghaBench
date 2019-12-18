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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QE_NUM_OF_SNUM ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 int of_property_read_variable_u8_array (struct device_node*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct device_node* qe_get_device_node () ; 
 int qe_num_of_snum ; 
 int /*<<< orphan*/  snum_state ; 
 int /*<<< orphan*/  snums ; 

__attribute__((used)) static void qe_snums_init(void)
{
	static const u8 snum_init_76[] = {
		0x04, 0x05, 0x0C, 0x0D, 0x14, 0x15, 0x1C, 0x1D,
		0x24, 0x25, 0x2C, 0x2D, 0x34, 0x35, 0x88, 0x89,
		0x98, 0x99, 0xA8, 0xA9, 0xB8, 0xB9, 0xC8, 0xC9,
		0xD8, 0xD9, 0xE8, 0xE9, 0x44, 0x45, 0x4C, 0x4D,
		0x54, 0x55, 0x5C, 0x5D, 0x64, 0x65, 0x6C, 0x6D,
		0x74, 0x75, 0x7C, 0x7D, 0x84, 0x85, 0x8C, 0x8D,
		0x94, 0x95, 0x9C, 0x9D, 0xA4, 0xA5, 0xAC, 0xAD,
		0xB4, 0xB5, 0xBC, 0xBD, 0xC4, 0xC5, 0xCC, 0xCD,
		0xD4, 0xD5, 0xDC, 0xDD, 0xE4, 0xE5, 0xEC, 0xED,
		0xF4, 0xF5, 0xFC, 0xFD,
	};
	static const u8 snum_init_46[] = {
		0x04, 0x05, 0x0C, 0x0D, 0x14, 0x15, 0x1C, 0x1D,
		0x24, 0x25, 0x2C, 0x2D, 0x34, 0x35, 0x88, 0x89,
		0x98, 0x99, 0xA8, 0xA9, 0xB8, 0xB9, 0xC8, 0xC9,
		0xD8, 0xD9, 0xE8, 0xE9, 0x08, 0x09, 0x18, 0x19,
		0x28, 0x29, 0x38, 0x39, 0x48, 0x49, 0x58, 0x59,
		0x68, 0x69, 0x78, 0x79, 0x80, 0x81,
	};
	struct device_node *qe;
	const u8 *snum_init;
	int i;

	bitmap_zero(snum_state, QE_NUM_OF_SNUM);
	qe_num_of_snum = 28; /* The default number of snum for threads is 28 */
	qe = qe_get_device_node();
	if (qe) {
		i = of_property_read_variable_u8_array(qe, "fsl,qe-snums",
						       snums, 1, QE_NUM_OF_SNUM);
		if (i > 0) {
			of_node_put(qe);
			qe_num_of_snum = i;
			return;
		}
		/*
		 * Fall back to legacy binding of using the value of
		 * fsl,qe-num-snums to choose one of the static arrays
		 * above.
		 */
		of_property_read_u32(qe, "fsl,qe-num-snums", &qe_num_of_snum);
		of_node_put(qe);
	}

	if (qe_num_of_snum == 76) {
		snum_init = snum_init_76;
	} else if (qe_num_of_snum == 28 || qe_num_of_snum == 46) {
		snum_init = snum_init_46;
	} else {
		pr_err("QE: unsupported value of fsl,qe-num-snums: %u\n", qe_num_of_snum);
		return;
	}
	memcpy(snums, snum_init, qe_num_of_snum);
}