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
typedef  int u8 ;
struct mlxsw_sp_acl_atcam_region {TYPE_2__* region; } ;
struct TYPE_3__ {int erp_id; } ;
struct mlxsw_sp_acl_atcam_entry {int /*<<< orphan*/ * enc_key; TYPE_1__ ht_key; } ;
struct mlxsw_afk_key_info {int dummy; } ;
typedef  int /*<<< orphan*/  erp_region_id ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {int id; struct mlxsw_afk_key_info* key_info; } ;

/* Variables and functions */
 int MLXSW_BLOOM_CHUNK_KEY_BYTES ; 
 int MLXSW_BLOOM_CHUNK_KEY_OFFSET ; 
 int MLXSW_BLOOM_CHUNK_PAD_BYTES ; 
 int MLXSW_BLOOM_KEY_CHUNKS ; 
 int MLXSW_BLOOM_KEY_CHUNK_BYTES ; 
 size_t* chunk_key_offsets ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int mlxsw_afk_key_info_blocks_count_get (struct mlxsw_afk_key_info*) ; 

__attribute__((used)) static void
mlxsw_sp_acl_bf_key_encode(struct mlxsw_sp_acl_atcam_region *aregion,
			   struct mlxsw_sp_acl_atcam_entry *aentry,
			   char *output, u8 *len)
{
	struct mlxsw_afk_key_info *key_info = aregion->region->key_info;
	u8 chunk_index, chunk_count, block_count;
	char *chunk = output;
	__be16 erp_region_id;

	block_count = mlxsw_afk_key_info_blocks_count_get(key_info);
	chunk_count = 1 + ((block_count - 1) >> 2);
	erp_region_id = cpu_to_be16(aentry->ht_key.erp_id |
				   (aregion->region->id << 4));
	for (chunk_index = MLXSW_BLOOM_KEY_CHUNKS - chunk_count;
	     chunk_index < MLXSW_BLOOM_KEY_CHUNKS; chunk_index++) {
		memset(chunk, 0, MLXSW_BLOOM_CHUNK_PAD_BYTES);
		memcpy(chunk + MLXSW_BLOOM_CHUNK_PAD_BYTES, &erp_region_id,
		       sizeof(erp_region_id));
		memcpy(chunk + MLXSW_BLOOM_CHUNK_KEY_OFFSET,
		       &aentry->enc_key[chunk_key_offsets[chunk_index]],
		       MLXSW_BLOOM_CHUNK_KEY_BYTES);
		chunk += MLXSW_BLOOM_KEY_CHUNK_BYTES;
	}
	*len = chunk_count * MLXSW_BLOOM_KEY_CHUNK_BYTES;
}