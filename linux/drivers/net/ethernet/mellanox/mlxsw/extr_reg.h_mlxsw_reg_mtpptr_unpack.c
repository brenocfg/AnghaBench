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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_mtpptr_rec_domain_number_get (char const*,unsigned int) ; 
 int /*<<< orphan*/  mlxsw_reg_mtpptr_rec_message_type_get (char const*,unsigned int) ; 
 int /*<<< orphan*/  mlxsw_reg_mtpptr_rec_sequence_id_get (char const*,unsigned int) ; 
 int mlxsw_reg_mtpptr_rec_timestamp_high_get (char const*,unsigned int) ; 
 int mlxsw_reg_mtpptr_rec_timestamp_low_get (char const*,unsigned int) ; 

__attribute__((used)) static inline void mlxsw_reg_mtpptr_unpack(const char *payload,
					   unsigned int rec,
					   u8 *p_message_type,
					   u8 *p_domain_number,
					   u16 *p_sequence_id,
					   u64 *p_timestamp)
{
	u32 timestamp_high, timestamp_low;

	*p_message_type = mlxsw_reg_mtpptr_rec_message_type_get(payload, rec);
	*p_domain_number = mlxsw_reg_mtpptr_rec_domain_number_get(payload, rec);
	*p_sequence_id = mlxsw_reg_mtpptr_rec_sequence_id_get(payload, rec);
	timestamp_high = mlxsw_reg_mtpptr_rec_timestamp_high_get(payload, rec);
	timestamp_low = mlxsw_reg_mtpptr_rec_timestamp_low_get(payload, rec);
	*p_timestamp = (u64)timestamp_high << 32 | timestamp_low;
}