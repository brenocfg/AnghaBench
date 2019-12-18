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
struct ubi_ec_hdr {int /*<<< orphan*/  hdr_crc; int /*<<< orphan*/  image_seq; int /*<<< orphan*/  data_offset; int /*<<< orphan*/  vid_hdr_offset; int /*<<< orphan*/  ec; scalar_t__ version; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  UBI_EC_HDR_SIZE ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,struct ubi_ec_hdr const*,int /*<<< orphan*/ ,int) ; 

void ubi_dump_ec_hdr(const struct ubi_ec_hdr *ec_hdr)
{
	pr_err("Erase counter header dump:\n");
	pr_err("\tmagic          %#08x\n", be32_to_cpu(ec_hdr->magic));
	pr_err("\tversion        %d\n", (int)ec_hdr->version);
	pr_err("\tec             %llu\n", (long long)be64_to_cpu(ec_hdr->ec));
	pr_err("\tvid_hdr_offset %d\n", be32_to_cpu(ec_hdr->vid_hdr_offset));
	pr_err("\tdata_offset    %d\n", be32_to_cpu(ec_hdr->data_offset));
	pr_err("\timage_seq      %d\n", be32_to_cpu(ec_hdr->image_seq));
	pr_err("\thdr_crc        %#08x\n", be32_to_cpu(ec_hdr->hdr_crc));
	pr_err("erase counter header hexdump:\n");
	print_hex_dump(KERN_DEBUG, "", DUMP_PREFIX_OFFSET, 32, 1,
		       ec_hdr, UBI_EC_HDR_SIZE, 1);
}