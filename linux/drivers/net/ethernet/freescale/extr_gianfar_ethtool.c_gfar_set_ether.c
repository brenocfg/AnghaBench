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
typedef  int u32 ;
struct filer_table {int dummy; } ;
struct ethhdr {int* h_source; int* h_dest; int /*<<< orphan*/  h_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  RQFCR_PID_DAH ; 
 int /*<<< orphan*/  RQFCR_PID_DAL ; 
 int /*<<< orphan*/  RQFCR_PID_ETY ; 
 int /*<<< orphan*/  RQFCR_PID_SAH ; 
 int /*<<< orphan*/  RQFCR_PID_SAL ; 
 int /*<<< orphan*/  RQFPR_EBC ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfar_set_attribute (int,int,int /*<<< orphan*/ ,struct filer_table*) ; 
 int /*<<< orphan*/  gfar_set_parse_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct filer_table*) ; 
 scalar_t__ is_broadcast_ether_addr (int*) ; 
 scalar_t__ is_zero_ether_addr (int*) ; 

__attribute__((used)) static void gfar_set_ether(struct ethhdr *value, struct ethhdr *mask,
			   struct filer_table *tab)
{
	u32 upper_temp_mask = 0;
	u32 lower_temp_mask = 0;

	/* Source address */
	if (!is_broadcast_ether_addr(mask->h_source)) {
		if (is_zero_ether_addr(mask->h_source)) {
			upper_temp_mask = 0xFFFFFFFF;
			lower_temp_mask = 0xFFFFFFFF;
		} else {
			upper_temp_mask = mask->h_source[0] << 16 |
					  mask->h_source[1] << 8  |
					  mask->h_source[2];
			lower_temp_mask = mask->h_source[3] << 16 |
					  mask->h_source[4] << 8  |
					  mask->h_source[5];
		}
		/* Upper 24bit */
		gfar_set_attribute(value->h_source[0] << 16 |
				   value->h_source[1] << 8  |
				   value->h_source[2],
				   upper_temp_mask, RQFCR_PID_SAH, tab);
		/* And the same for the lower part */
		gfar_set_attribute(value->h_source[3] << 16 |
				   value->h_source[4] << 8  |
				   value->h_source[5],
				   lower_temp_mask, RQFCR_PID_SAL, tab);
	}
	/* Destination address */
	if (!is_broadcast_ether_addr(mask->h_dest)) {
		/* Special for destination is limited broadcast */
		if ((is_broadcast_ether_addr(value->h_dest) &&
		    is_zero_ether_addr(mask->h_dest))) {
			gfar_set_parse_bits(RQFPR_EBC, RQFPR_EBC, tab);
		} else {
			if (is_zero_ether_addr(mask->h_dest)) {
				upper_temp_mask = 0xFFFFFFFF;
				lower_temp_mask = 0xFFFFFFFF;
			} else {
				upper_temp_mask = mask->h_dest[0] << 16 |
						  mask->h_dest[1] << 8  |
						  mask->h_dest[2];
				lower_temp_mask = mask->h_dest[3] << 16 |
						  mask->h_dest[4] << 8  |
						  mask->h_dest[5];
			}

			/* Upper 24bit */
			gfar_set_attribute(value->h_dest[0] << 16 |
					   value->h_dest[1] << 8  |
					   value->h_dest[2],
					   upper_temp_mask, RQFCR_PID_DAH, tab);
			/* And the same for the lower part */
			gfar_set_attribute(value->h_dest[3] << 16 |
					   value->h_dest[4] << 8  |
					   value->h_dest[5],
					   lower_temp_mask, RQFCR_PID_DAL, tab);
		}
	}

	gfar_set_attribute(be16_to_cpu(value->h_proto),
			   be16_to_cpu(mask->h_proto),
			   RQFCR_PID_ETY, tab);
}