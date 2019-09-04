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
typedef  int /*<<< orphan*/  u32 ;
struct intel_encoder {int port; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum intel_output_type { ____Placeholder_intel_output_type } intel_output_type ;

/* Variables and functions */
 int PORT_A ; 
 int PORT_B ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  icl_combo_phy_ddi_vswing_sequence (struct intel_encoder*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void icl_ddi_vswing_sequence(struct intel_encoder *encoder, u32 level,
				    enum intel_output_type type)
{
	enum port port = encoder->port;

	if (port == PORT_A || port == PORT_B)
		icl_combo_phy_ddi_vswing_sequence(encoder, level, type);
	else
		/* Not Implemented Yet */
		WARN_ON(1);
}