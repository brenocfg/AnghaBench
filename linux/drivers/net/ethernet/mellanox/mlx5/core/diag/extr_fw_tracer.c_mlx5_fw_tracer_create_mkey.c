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
typedef  int /*<<< orphan*/  u64 ;
typedef  void u32 ;
struct TYPE_2__ {int pdn; int /*<<< orphan*/  mkey; scalar_t__ size; scalar_t__ dma; } ;
struct mlx5_fw_tracer {TYPE_1__ buff; struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (void*,void*,int /*<<< orphan*/ ) ; 
 int MLX5_MKC_ACCESS_MODE_MTT ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5_SET64 (void*,void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int MLX5_ST_SZ_BYTES (void*) ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int TRACER_BUFFER_PAGE_NUM ; 
 int /*<<< orphan*/  access_mode_1_0 ; 
 int /*<<< orphan*/  bsf_octword_size ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 void* create_mkey_in ; 
 int /*<<< orphan*/  klm_pas_mtt ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  len ; 
 int /*<<< orphan*/  log_page_size ; 
 int /*<<< orphan*/  lr ; 
 int /*<<< orphan*/  lw ; 
 int /*<<< orphan*/  memory_key_mkey_entry ; 
 int mlx5_core_create_mkey (struct mlx5_core_dev*,int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  pd ; 
 int /*<<< orphan*/  qpn ; 
 int round_up (int,int) ; 
 int /*<<< orphan*/  start_addr ; 
 int /*<<< orphan*/  translations_octword_actual_size ; 
 int /*<<< orphan*/  translations_octword_size ; 

__attribute__((used)) static int mlx5_fw_tracer_create_mkey(struct mlx5_fw_tracer *tracer)
{
	struct mlx5_core_dev *dev = tracer->dev;
	int err, inlen, i;
	__be64 *mtt;
	void *mkc;
	u32 *in;

	inlen = MLX5_ST_SZ_BYTES(create_mkey_in) +
			sizeof(*mtt) * round_up(TRACER_BUFFER_PAGE_NUM, 2);

	in = kvzalloc(inlen, GFP_KERNEL);
	if (!in)
		return -ENOMEM;

	MLX5_SET(create_mkey_in, in, translations_octword_actual_size,
		 DIV_ROUND_UP(TRACER_BUFFER_PAGE_NUM, 2));
	mtt = (u64 *)MLX5_ADDR_OF(create_mkey_in, in, klm_pas_mtt);
	for (i = 0 ; i < TRACER_BUFFER_PAGE_NUM ; i++)
		mtt[i] = cpu_to_be64(tracer->buff.dma + i * PAGE_SIZE);

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
	MLX5_SET(mkc, mkc, access_mode_1_0, MLX5_MKC_ACCESS_MODE_MTT);
	MLX5_SET(mkc, mkc, lr, 1);
	MLX5_SET(mkc, mkc, lw, 1);
	MLX5_SET(mkc, mkc, pd, tracer->buff.pdn);
	MLX5_SET(mkc, mkc, bsf_octword_size, 0);
	MLX5_SET(mkc, mkc, qpn, 0xffffff);
	MLX5_SET(mkc, mkc, log_page_size, PAGE_SHIFT);
	MLX5_SET(mkc, mkc, translations_octword_size,
		 DIV_ROUND_UP(TRACER_BUFFER_PAGE_NUM, 2));
	MLX5_SET64(mkc, mkc, start_addr, tracer->buff.dma);
	MLX5_SET64(mkc, mkc, len, tracer->buff.size);
	err = mlx5_core_create_mkey(dev, &tracer->buff.mkey, in, inlen);
	if (err)
		mlx5_core_warn(dev, "FWTracer: Failed to create mkey, %d\n", err);

	kvfree(in);

	return err;
}