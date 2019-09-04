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
struct mlxfw_mfa2_tlv_package_descriptor {int /*<<< orphan*/  cb_archive_size; int /*<<< orphan*/  cb_offset; int /*<<< orphan*/  num_components; int /*<<< orphan*/  num_devices; } ;
struct mlxfw_mfa2_tlv_multi {int dummy; } ;
struct mlxfw_mfa2_tlv {int dummy; } ;
struct mlxfw_mfa2_file {void* cb; int cb_archive_size; void* component_count; void* dev_count; int /*<<< orphan*/  first_dev; int /*<<< orphan*/  first_component; struct firmware const* fw; } ;
struct firmware {void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct mlxfw_mfa2_file* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NLA_ALIGN (int) ; 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct mlxfw_mfa2_file* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlxfw_mfa2_file*) ; 
 int /*<<< orphan*/  mlxfw_mfa2_file_validate (struct mlxfw_mfa2_file*) ; 
 int mlxfw_mfa2_fingerprint_len ; 
 int /*<<< orphan*/  mlxfw_mfa2_tlv_advance (struct mlxfw_mfa2_file*,int /*<<< orphan*/ ,void*) ; 
 struct mlxfw_mfa2_tlv* mlxfw_mfa2_tlv_get (struct mlxfw_mfa2_file*,void const*) ; 
 struct mlxfw_mfa2_tlv* mlxfw_mfa2_tlv_multi_child (struct mlxfw_mfa2_file*,struct mlxfw_mfa2_tlv_multi const*) ; 
 struct mlxfw_mfa2_tlv_multi* mlxfw_mfa2_tlv_multi_get (struct mlxfw_mfa2_file*,struct mlxfw_mfa2_tlv const*) ; 
 int /*<<< orphan*/  mlxfw_mfa2_tlv_next (struct mlxfw_mfa2_file*,struct mlxfw_mfa2_tlv const*) ; 
 struct mlxfw_mfa2_tlv_package_descriptor* mlxfw_mfa2_tlv_package_descriptor_get (struct mlxfw_mfa2_file*,struct mlxfw_mfa2_tlv const*) ; 
 int /*<<< orphan*/  mlxfw_mfa2_valid_ptr (struct mlxfw_mfa2_file*,void const*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

struct mlxfw_mfa2_file *mlxfw_mfa2_file_init(const struct firmware *fw)
{
	const struct mlxfw_mfa2_tlv_package_descriptor *pd;
	const struct mlxfw_mfa2_tlv_multi *multi;
	const struct mlxfw_mfa2_tlv *multi_child;
	const struct mlxfw_mfa2_tlv *first_tlv;
	struct mlxfw_mfa2_file *mfa2_file;
	const void *first_tlv_ptr;
	const void *cb_top_ptr;

	mfa2_file = kcalloc(1, sizeof(*mfa2_file), GFP_KERNEL);
	if (!mfa2_file)
		return ERR_PTR(-ENOMEM);

	mfa2_file->fw = fw;
	first_tlv_ptr = fw->data + NLA_ALIGN(mlxfw_mfa2_fingerprint_len);
	first_tlv = mlxfw_mfa2_tlv_get(mfa2_file, first_tlv_ptr);
	if (!first_tlv) {
		pr_err("Could not parse package descriptor TLV\n");
		goto err_out;
	}

	multi = mlxfw_mfa2_tlv_multi_get(mfa2_file, first_tlv);
	if (!multi) {
		pr_err("First TLV is not of valid multi type\n");
		goto err_out;
	}

	multi_child = mlxfw_mfa2_tlv_multi_child(mfa2_file, multi);
	if (!multi_child)
		goto err_out;

	pd = mlxfw_mfa2_tlv_package_descriptor_get(mfa2_file, multi_child);
	if (!pd) {
		pr_err("Could not parse package descriptor TLV\n");
		goto err_out;
	}

	mfa2_file->first_dev = mlxfw_mfa2_tlv_next(mfa2_file, first_tlv);
	if (!mfa2_file->first_dev) {
		pr_err("First device TLV is not valid\n");
		goto err_out;
	}

	mfa2_file->dev_count = be16_to_cpu(pd->num_devices);
	mfa2_file->first_component = mlxfw_mfa2_tlv_advance(mfa2_file,
							    mfa2_file->first_dev,
							    mfa2_file->dev_count);
	mfa2_file->component_count = be16_to_cpu(pd->num_components);
	mfa2_file->cb = fw->data + NLA_ALIGN(be32_to_cpu(pd->cb_offset));
	if (!mlxfw_mfa2_valid_ptr(mfa2_file, mfa2_file->cb)) {
		pr_err("Component block is out side the file\n");
		goto err_out;
	}
	mfa2_file->cb_archive_size = be32_to_cpu(pd->cb_archive_size);
	cb_top_ptr = mfa2_file->cb + mfa2_file->cb_archive_size - 1;
	if (!mlxfw_mfa2_valid_ptr(mfa2_file, cb_top_ptr)) {
		pr_err("Component block size is too big\n");
		goto err_out;
	}

	if (!mlxfw_mfa2_file_validate(mfa2_file))
		goto err_out;
	return mfa2_file;
err_out:
	kfree(mfa2_file);
	return ERR_PTR(-EINVAL);
}