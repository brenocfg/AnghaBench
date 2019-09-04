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
typedef  int /*<<< orphan*/  u16 ;
typedef  enum ib_signature_type { ____Placeholder_ib_signature_type } ib_signature_type ;

/* Variables and functions */
#define  IB_SIG_TYPE_T10_DIF 128 
 int /*<<< orphan*/  MLX5_DIF_SIZE ; 

__attribute__((used)) static u16 prot_field_size(enum ib_signature_type type)
{
	switch (type) {
	case IB_SIG_TYPE_T10_DIF:
		return MLX5_DIF_SIZE;
	default:
		return 0;
	}
}