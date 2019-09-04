#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ucmd ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct mlx5_ib_create_cq {int flags; int cqe_size; int cqe_comp_en; int /*<<< orphan*/  cqe_comp_res_format; int /*<<< orphan*/  buf_addr; int /*<<< orphan*/  db_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  umem; } ;
struct mlx5_ib_cq {TYPE_2__ buf; int /*<<< orphan*/  db; int /*<<< orphan*/  private_flags; } ;
struct ib_udata {int inlen; } ;
struct ib_ucontext {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_6__ {int* sys_pages; } ;
struct TYPE_8__ {TYPE_1__ bfregi; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_ACCESS_LOCAL_WRITE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MLX5_ADAPTER_PAGE_SHIFT ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_FLD_SZ_BYTES (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_IB_CQ_PR_FLAGS_CQE_128_PAD ; 
 int MLX5_IB_CREATE_CQ_FLAGS_CQE_128B_PAD ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cq_context ; 
 int /*<<< orphan*/  cqe_128_always ; 
 int /*<<< orphan*/  cqe_comp_en ; 
 int /*<<< orphan*/  cqe_compression ; 
 int /*<<< orphan*/  cqe_compression_128 ; 
 int /*<<< orphan*/  create_cq_in ; 
 scalar_t__ ib_copy_from_udata (struct mlx5_ib_create_cq*,struct ib_udata*,size_t) ; 
 int /*<<< orphan*/  ib_umem_get (struct ib_ucontext*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_page_size ; 
 int /*<<< orphan*/  mini_cqe_res_format ; 
 int mini_cqe_res_format_to_hw (struct mlx5_ib_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_cont_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*,int /*<<< orphan*/ *) ; 
 int mlx5_ib_db_map_user (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_db_unmap_user (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  mlx5_ib_populate_pas (struct mlx5_ib_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int) ; 
 TYPE_3__* to_mucontext (struct ib_ucontext*) ; 

__attribute__((used)) static int create_cq_user(struct mlx5_ib_dev *dev, struct ib_udata *udata,
			  struct ib_ucontext *context, struct mlx5_ib_cq *cq,
			  int entries, u32 **cqb,
			  int *cqe_size, int *index, int *inlen)
{
	struct mlx5_ib_create_cq ucmd = {};
	size_t ucmdlen;
	int page_shift;
	__be64 *pas;
	int npages;
	int ncont;
	void *cqc;
	int err;

	ucmdlen = udata->inlen < sizeof(ucmd) ?
		  (sizeof(ucmd) - sizeof(ucmd.flags)) : sizeof(ucmd);

	if (ib_copy_from_udata(&ucmd, udata, ucmdlen))
		return -EFAULT;

	if (ucmdlen == sizeof(ucmd) &&
	    (ucmd.flags & ~(MLX5_IB_CREATE_CQ_FLAGS_CQE_128B_PAD)))
		return -EINVAL;

	if (ucmd.cqe_size != 64 && ucmd.cqe_size != 128)
		return -EINVAL;

	*cqe_size = ucmd.cqe_size;

	cq->buf.umem = ib_umem_get(context, ucmd.buf_addr,
				   entries * ucmd.cqe_size,
				   IB_ACCESS_LOCAL_WRITE, 1);
	if (IS_ERR(cq->buf.umem)) {
		err = PTR_ERR(cq->buf.umem);
		return err;
	}

	err = mlx5_ib_db_map_user(to_mucontext(context), ucmd.db_addr,
				  &cq->db);
	if (err)
		goto err_umem;

	mlx5_ib_cont_pages(cq->buf.umem, ucmd.buf_addr, 0, &npages, &page_shift,
			   &ncont, NULL);
	mlx5_ib_dbg(dev, "addr 0x%llx, size %u, npages %d, page_shift %d, ncont %d\n",
		    ucmd.buf_addr, entries * ucmd.cqe_size, npages, page_shift, ncont);

	*inlen = MLX5_ST_SZ_BYTES(create_cq_in) +
		 MLX5_FLD_SZ_BYTES(create_cq_in, pas[0]) * ncont;
	*cqb = kvzalloc(*inlen, GFP_KERNEL);
	if (!*cqb) {
		err = -ENOMEM;
		goto err_db;
	}

	pas = (__be64 *)MLX5_ADDR_OF(create_cq_in, *cqb, pas);
	mlx5_ib_populate_pas(dev, cq->buf.umem, page_shift, pas, 0);

	cqc = MLX5_ADDR_OF(create_cq_in, *cqb, cq_context);
	MLX5_SET(cqc, cqc, log_page_size,
		 page_shift - MLX5_ADAPTER_PAGE_SHIFT);

	*index = to_mucontext(context)->bfregi.sys_pages[0];

	if (ucmd.cqe_comp_en == 1) {
		int mini_cqe_format;

		if (!((*cqe_size == 128 &&
		       MLX5_CAP_GEN(dev->mdev, cqe_compression_128)) ||
		      (*cqe_size == 64  &&
		       MLX5_CAP_GEN(dev->mdev, cqe_compression)))) {
			err = -EOPNOTSUPP;
			mlx5_ib_warn(dev, "CQE compression is not supported for size %d!\n",
				     *cqe_size);
			goto err_cqb;
		}

		mini_cqe_format =
			mini_cqe_res_format_to_hw(dev,
						  ucmd.cqe_comp_res_format);
		if (mini_cqe_format < 0) {
			err = mini_cqe_format;
			mlx5_ib_dbg(dev, "CQE compression res format %d error: %d\n",
				    ucmd.cqe_comp_res_format, err);
			goto err_cqb;
		}

		MLX5_SET(cqc, cqc, cqe_comp_en, 1);
		MLX5_SET(cqc, cqc, mini_cqe_res_format, mini_cqe_format);
	}

	if (ucmd.flags & MLX5_IB_CREATE_CQ_FLAGS_CQE_128B_PAD) {
		if (*cqe_size != 128 ||
		    !MLX5_CAP_GEN(dev->mdev, cqe_128_always)) {
			err = -EOPNOTSUPP;
			mlx5_ib_warn(dev,
				     "CQE padding is not supported for CQE size of %dB!\n",
				     *cqe_size);
			goto err_cqb;
		}

		cq->private_flags |= MLX5_IB_CQ_PR_FLAGS_CQE_128_PAD;
	}

	return 0;

err_cqb:
	kvfree(*cqb);

err_db:
	mlx5_ib_db_unmap_user(to_mucontext(context), &cq->db);

err_umem:
	ib_umem_release(cq->buf.umem);
	return err;
}